// This file doesn't really exist, but it doesn't matter, a "PermissionsDenied" error should be thrown.
const code = `import "file:///local_file.ts";`;
const blob = new Blob([code]);
await import(URL.createObjectURL(blob));
