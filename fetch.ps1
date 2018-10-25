
Set-StrictMode -Version 5
$ErrorActionPreference = "Stop"

function Get-TempName {
  $env:TEMP + "\" + [System.IO.Path]::GetRandomFileName()
}

function Get-LatestVersion([string] $Remote, [string] $Pattern) {
  $latest_version = git ls-remote $Remote | 
    ? { $_ -match '^(?<sha>\S*)\t(?<refspec>\S*)$' } |
    % { $Matches } |
    ? { $_.refspec -match $Pattern } |
    ? { $Matches[1] -match '^(\d+)\.(\d+)\.(\d+)$' } |
    % { $_.version  = $Matches[0]
        $_.ver_nums =   1..3 | % { $Matches[$_] } 
        $_.ordinal  = ((1..3 | % { $Matches[$_].PadLeft(3, "0") }) -join '') + 0
        $_ } |   
    % { New-Object -TypeName PSObject -Property $_ } |
    Sort-Object -Property "ordinal" -Descending  |
    Select-Object -First 1
  git fetch $Remote  $latest_version.sha + ":AUTOGRAFT_HEAD"
}

$env:GIT_DIR = git rev-parse --absolute-git-dir
$env:GIT_WORKTREE = Get-TempName
$env:GIT_INDEX_FILE = Get-TempName

new-item $env:GIT_WORKTREE -ItemType Directory | Out-Null
push-location $env:GIT_WORKTREE

Get-LatestVersion -Remote "git://github.com/nodejs/node" -Pattern '^refs/tags/v(10\..*\d)$'
