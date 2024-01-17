import { EnigmaType } from "@customTypes/EnigmaType";

export async function enigma_post(data: EnigmaType) {
  const response = await fetch("http://localhost:17576", {
    method: "POST",
    body: JSON.stringify(data),
    // set same-origin policy
    credentials: "same-origin",

    // set CORS policy
    mode: "no-cors",
  });

  return response;
}
