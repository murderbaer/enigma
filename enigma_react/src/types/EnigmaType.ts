export enum EnigmaModel {
  EnigmaM3 = "M3",
  EnigmaM4 = "M4",
}

export const EnigmaRotor = {
  I: 1,
  II: 2,
  III: 3,
  IV: 4,
  V: 5,
  VI: 6,
  VII: 7,
  VIII: 8,
};

export const EnigmaReflector = {
  B: "B",
  C: "C",
  BThin: "BThin",
  CThin: "CThin",
};

export type EnigmaType = {
  model: EnigmaModel;
  rotors: number[];
  reflector: string;
  ringSettings: number[];
  rotorPositions: number[];
  plugboard: string;
  message: string;
};
