let translated_text = "";

function get_ws_endpoint() {
  endpoint = window.location.href + "ws/translate"
  endpoint = endpoint.replace("https", "wss")
  endpoint = endpoint.replace("http", "ws")
  return endpoint
}
let ws = new WebSocket(get_ws_endpoint())
ws.onmessage = (message) => {
  set_success_translator();
  set_translation(message.data);
}

function ws_translate() {
  if (ws != null) {
    const text_to_translate = document.getElementById("yololInput").value;
    if (text_to_translate !== translated_text) {
      translated_text = text_to_translate;
      ws.send(text_to_translate)
    }
  } else {
    // Fallback in case websocket stuff does not work
    translate()
  }
}

function set_failure_translator() {
  document.getElementById("title").innerText = "💀 Failing translator";
}

function set_success_translator() {
  document.getElementById("title").innerText = "Yolol Translator";
}


function set_translation(text) {
  document.getElementById("yololOutput").value = text;
}

function translate() {
  const text_to_translate = document.getElementById("yololInput").value;
  if (text_to_translate !== translated_text) {
    translated_text = text_to_translate;
    fetch("/translate", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ text: text_to_translate })
    }).then(
      (res) => {
        if (res.status !== 200) {
          set_failure_translator();
        } else {
          set_success_translator();
        }
        return res.text();
      }
    ).then(
      (text) => {
        text_without_quotes = text.substring(1, text.length - 1);
        set_translation(text_without_quotes);
      }
    );
  }
}

// Not ideal, but it will be changed when I will implement and use the websocket api
setInterval(ws_translate, 500);

function copyToClipboard() {
  // Get the text field
  var copyText = document.getElementById("yololOutput");

  // Select the text field
  copyText.select();
  copyText.setSelectionRange(0, 99999); // For mobile devices

  // Copy the text inside the text field
  navigator.clipboard.writeText(copyText.value);
}