import { cache } from "https://deno.land/x/cache@0.2.13/mod.ts";

function suffix() {
  switch (Deno.build.os) {
    case "darwin":
      return ".dylib";
    case "windows":
      return ".dll";
    case "linux":
      return ".so";
  }
}

const lib = await cache(
  "https://github.com/ahgilak/popup/releases/latest/download/libpopup" + suffix(),
);

export default lib.path;
