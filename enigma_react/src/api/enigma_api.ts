import { EnigmaType } from "@customTypes/EnigmaType";

export async function enigma_post(data: EnigmaType) {
  // rotorposition is a number array, it needs to be a string where A=1 etc
  const rotorPositions = data.rotorPositions
    .map((position) => String.fromCharCode(64 + position))
    .toString()
    .replace(/,/g, "");
  const ringSettings = data.ringSettings
    .map((setting) => String.fromCharCode(64 + setting))
    .toString()
    .replace(/,/g, "");

  const request = {
    model: data.model,
    rotors: data.rotors,
    ringSettings: ringSettings,
    rotorPositions: rotorPositions,
    reflector: data.reflector,
    plugboard: data.plugboard,
    message: data.message,
  };

  console.log(request);

  const response = await fetch("http://enigma-backend-1:17576", {
    method: "POST",
    body: JSON.stringify(request),
  });

  return response;
}
