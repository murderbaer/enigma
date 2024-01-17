import { createSlice } from "@reduxjs/toolkit";
import {
  EnigmaType,
  EnigmaModel,
  EnigmaRotor,
  EnigmaReflector,
} from "@customTypes/EnigmaType";

const initialState: EnigmaType = {
  model: EnigmaModel.EnigmaM3,
  rotors: [EnigmaRotor.I, EnigmaRotor.II, EnigmaRotor.III],
  ringSettings: [1, 1, 1],
  rotorPositions: [1, 1, 1],
  reflector: EnigmaReflector.C,
  plugboard: "",
  message: "AAA",
};

const EnigmaSlice = createSlice({
  name: "enigma",
  initialState,
  reducers: {
    setEnigmaType: (state: EnigmaType, action) => {
      state.model = action.payload;
    },
    addToRotor: (state: EnigmaType, action) => {
      const { position } = action.payload;
      state.rotors[position] =
        (state.rotors[position] % Object.keys(EnigmaRotor).length) + 1;
    },
    subractToRotor: (state: EnigmaType, action) => {
      const { position } = action.payload;
      let newValue = state.rotors[position] - 1;

      if (newValue === 0) {
        newValue = Object.keys(EnigmaRotor).length;
      }

      state.rotors[position] = newValue;
    },
    addToRingSetting: (state: EnigmaType, action) => {
      const { position } = action.payload;
      state.ringSettings[position] = (state.ringSettings[position] % 26) + 1;
    },
    subtractToRingSetting: (state: EnigmaType, action) => {
      const { position } = action.payload;
      let newValue = state.ringSettings[position] - 1;

      if (newValue === 0) {
        newValue = 26;
      }

      state.ringSettings[position] = newValue;
    },
    addToRotorPosition: (state: EnigmaType, action) => {
      const { position } = action.payload;
      state.rotorPositions[position] =
        (state.rotorPositions[position] % 26) + 1;
    },
    subtractToRotorPosition: (state: EnigmaType, action) => {
      const { position } = action.payload;
      let newValue = state.rotorPositions[position] - 1;

      if (newValue === 0) {
        newValue = 26;
      }

      state.rotorPositions[position] = newValue;
    },
    setReflector: (state: EnigmaType, action) => {
      state.reflector = action.payload;
    },
    setPlugboard: (state: EnigmaType, action) => {
      state.plugboard = action.payload;
    },
    setMessage: (state: EnigmaType, action) => {
      state.message = action.payload;
    },
  },
});

export const EnigmaActions = EnigmaSlice.actions;

export const EnigmaReducer = EnigmaSlice.reducer;

export default EnigmaSlice;
