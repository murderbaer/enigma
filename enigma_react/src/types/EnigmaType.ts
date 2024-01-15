export enum EnigmaModel {
  EnigmaM3 = "M3",
  EnigmaM4 = "M4",
}

export const EnigmaRotor = {
  I: "I",
  II: "II",
  III: "III",
  IV: "IV",
  V: "V",
  VI: "VI",
  VII: "VII",
  VIII: "VIII",
};

export const EnigmaReflector = {
  B: "B",
  C: "C",
  BThin: "BThin",
  CThin: "CThin",
};

export type EnigmaType = {
  model: EnigmaModel;
  rotors: string[];
  reflector: string;
  ringSettings: string;
  rotorPositions: string;
  plugboard: string;
  message: string;
};
