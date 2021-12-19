import lib from "./lib.ts";

const encoder = new TextEncoder();

const popup = Deno.dlopen(lib, {
  init: { parameters: [], result: "void" },
  alert: { parameters: ["pointer"], result: "void" },
  confirm: { parameters: ["pointer"], result: "u32" },
  prompt: { parameters: ["pointer", "pointer"], result: "pointer" },
});

popup.symbols.init();

function toCString(str = "") {
  return encoder.encode(str + "\0");
}

export function alert(message?: string) {
  popup.symbols.alert(toCString(message));
}

export function confirm(message?: string) {
  return Boolean(popup.symbols.confirm(toCString(message)));
}

export function prompt(message?: string, defaultValue?: string) {
  const ptr = popup.symbols.prompt(
    toCString(message),
    toCString(defaultValue),
  ) as Deno.UnsafePointer;

  if (ptr.valueOf() === 0n) {
    return null;
  }

  const ptrView = new Deno.UnsafePointerView(ptr);
  return ptrView.getCString();
}

self.addEventListener("unload", () => popup.close());
