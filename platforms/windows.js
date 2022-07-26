import * as win32 from "https://deno.land/x/win32@0.1.1/mod.ts";

export function alert(message) {
  win32.MessageBox(0n, message, "Alert", win32.MB_OK);
}

export function confirm(message) {
  const id = win32.MessageBox(0n, message, "Confirm", win32.MB_OKCANCE);

  return id === win32.IDOK;
}

export function prompt(message, defaultValue) {
  return window.prompt(message, defaultValue);
}
