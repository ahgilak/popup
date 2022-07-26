/// <reference types="./popup.d.ts" />

export const { alert, confirm, prompt } = await import(
  `./platforms/${Deno.build.os}.js`
);
