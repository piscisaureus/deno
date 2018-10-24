
import json
import os
import sys
import re
from os.path import abspath, basename, dirname, join, normpath, relpath

# Locate GYP and add it to PYTHONPATH so we can import it. Also add this file's
# directory, so GYP can find us when it tries to invoke the generator.
script_dir = dirname(abspath(__file__))
gyp_pylib_dir = normpath(script_dir + "/../gyp/pylib")
sys.path += [ script_dir, gyp_pylib_dir ]

import gyp
import gyp.common

# This is for debugging.
def dump(o):
  class AnythingToJSONEncoder(json.JSONEncoder):
    def default(self, obj):
        # Map a set to a list.
        if type(obj) is set:
            return [i for i in obj]
        # Convert any other object to a dict.
        dict = {}
        for key in dir(obj):
          val = getattr(obj, key)
          # Skip methods.
          if getattr(val, "__call__", None) is not None:
            continue
          # Try to avoid infinite recursion.
          if val == obj:
            continue
          dict[key] = val
        return dict
        
  # Convert to JSON, then pretty print.
  return json.dump(o, sys.stderr, indent=2, separators=(',', ': '), cls=AnythingToJSONEncoder)

# Placeholders that can be used when mapping GYP rules to for GN action_foreach
# targets. This list is not complete.
generator_default_variables = {
  "RULE_INPUT_DIRNAME":"{{source_dir}}",
  "RULE_INPUT_NAME":"{{source_file_part}}",
  "RULE_INPUT_PATH":"{{source}}",
  "RULE_INPUT_ROOT":"{{source_name_part}}",
}
 
def MapQualifiedName(original, mappings):
    # Map the name to something like 'mygypfile.gyp#mytarget'.
    (gypfile, target_name, _) = gyp.common.ParseQualifiedTarget(original)
    mapped = basename(gypfile) + "--" + target_name
    
    if mapped in mappings:
      # This mapping is very simplistic. Check for collisions.
      assert mappings[mapped] == original
    else:
      # Store this new mapping.
      mappings[mapped] = original
      
    return mapped
  
def GenerateOutput(qualified_names, targets, data, params):
  # A dict that remembers what qualified names were remapped to.
  qualified_name_mappings = {}
  # A list of target scopes that will be returned to GN. 
  gn_targets = []  
  
  for qualified_name, target in targets.iteritems():
    # Add the name of the gypfile. It's not available in the info dict.
    (gypfile, _, _) = gyp.common.ParseQualifiedTarget(qualified_name)
    target["gypfile"] = gypfile
    
    # Determine the base path for this target. Filenames inside the info
    # dict are relative to this base path.
    target["gypfile_dir"] = abspath(dirname(gypfile));
       
    # Remove the "-l" prefix from libraries. GN does not support this. Store the
    # filtered list as "libs" since that is the variable name GN uses.
    if "libraries" in target:
      target["libs"] = [re.sub("^-l", "", i) for i in target.pop("libraries", None)]
    
    # The 'qualified name' is how targets reference other other targets in the
    # 'dependencies' list, so we need it. It can't be a key in the output dict,
    # because it's not a valid GN key, so we add it as anoter value item.
    # Map the name to something simpler so that it's acceptable to GN.
    target["qualified_name"] = MapQualifiedName(qualified_name, qualified_name_mappings)

    # Map the qualifiednames of dependencies.
    if "dependencies" in target:
      target["dependencies"] = [MapQualifiedName(i, qualified_name_mappings) for i in target["dependencies"]]
       
    # In GN it isn't possible to do the equivalent of 
    # `configurations[default_configuration]`, so we pre-emptively assigned it
    # to a key with a known name ('_default').
    configurations = target["configurations"]
    configurations["_default"] = configurations[target["default_configuration"]]
    
    # We know nothing about toolsets.
    assert target["toolset"] == "target"
    target.pop("toolset", None)
    
    # Remove variables - we don't need them.
    target.pop("variables", None)
    
    # Add to the list that we'll pass to GN at the end.
    gn_targets += [target]

  # Write GN information to stdout in json format.  
  json.dump(gn_targets, sys.stdout)
  
  # Use this to debug.
  # dump(gn_targets)
  # dump(params)
       
def main(argv):
    return gyp.main(argv + ["-f", "gyp2gn.py"])

if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))

    