import * as gi from "https://deno.land/x/deno_gi@v0.0.1/mod.js";

const Gtk = gi.require("Gtk", "4.0");
const GLib = gi.require("GLib", "2.0");

Gtk.init();
const loop = GLib.MainLoop.new(null, false);
const parent = new Gtk.Window();

export function alert(message) {
  const dialog = new Gtk.MessageDialog({
    transientFor: parent,
    visible: true,
    text: message,
    buttons: Gtk.ButtonsType.OK,
  });

  dialog.on("response", () => {
    dialog.destroy();
    loop.quit();
  });

  loop.run();
}

export function confirm(message) {
  let response = false;

  const dialog = new Gtk.MessageDialog({
    transientFor: parent,
    visible: true,
    text: message,
    buttons: Gtk.ButtonsType.OK_CANCEL,
  });

  dialog.on("response", (_, responseId) => {
    response = responseId === Gtk.ResponseType.OK;
    dialog.destroy();
    loop.quit();
  });

  loop.run();

  return response;
}

export function prompt(message, defaultValue = "") {
  let response = null;
  const buffer = Gtk.EntryBuffer.new(defaultValue, defaultValue.length);
  const entry = Gtk.Entry.newWithBuffer(buffer);

  const dialog = new Gtk.MessageDialog({
    transientFor: parent,
    visible: true,
    text: message,
    buttons: Gtk.ButtonsType.OK_CANCEL,
  });

  const contentArea = dialog.getContentArea();
  contentArea.append(entry);
  contentArea.setMarginStart(10);
  contentArea.setMarginEnd(10);

  dialog.on("response", (_, responseId) => {
    if (responseId === Gtk.ResponseType.OK) {
      response = buffer.getText(-1);
    }
    dialog.destroy();
    loop.quit();
  });

  loop.run();

  return response;
}
