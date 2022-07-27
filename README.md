# Popup

GUI for javascript standard popup's in [deno](https://deno.land/).

## Example

```javascript
import { alert, confirm } from "https://deno.land/x/popup/mod.ts";

if (confirm("Press a button!") == true) {
  alert("You pressed OK!");
} else {
  alert("You canceled!");
}
```

## Prerequisites

- on linux `gtk4` package is needed.
