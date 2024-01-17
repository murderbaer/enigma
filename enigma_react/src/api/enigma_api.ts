import { EnigmaType } from "@customTypes/EnigmaType";

export async function enigma_post(data: EnigmaType) {
  const response = await fetch(
    "http://127.0.0.1:17576",
     {
            method: "POST",
            body: JSON.stringify(data),
          }
          );

  return response;
}
