# Popup (WIP)

GUI for javascript standard popup's in [deno](https://deno.land/).

## Example

```typescript
import { prompt } from "https://deno.land/x/popup/mod.ts";

prompt("Are you feeling lucky?", "sure");
```

result will look like this:

![screenshot](./img/screenshot.png)

## Overwrite Global Functions

```typescript
import { alert, confirm, prompt } from "https://deno.land/x/popup/mod.ts";

window.alert = alert;
window.prompt = prompt;
window.confirm = confirm;
```

## Prerequisites

### Linux

- package `gtk4` should be installed.

### Windows

- Install `MinGW` and `mingw-w64-x86_64-gtk4`.
- Add `C:\msys64\mingw64\bin` to path.
