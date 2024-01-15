import { createSlice } from "@reduxjs/toolkit";
import {
  EnigmaType,
  EnigmaModel,
  EnigmaRotor,
  EnigmaReflector,
} from "../../types/EnigmaType";

const initialState: EnigmaType = {
  model: EnigmaModel.EnigmaM3,
  rotors: [EnigmaRotor.I, EnigmaRotor.II, EnigmaRotor.III],
  ringSettings: "AAA",
  rotorPositions: "ABC",
  reflector: EnigmaReflector.B,
  plugboard: "",
  message: "",
};

const EnigmaSlice = createSlice({
  name: "enigma",
  initialState,
  reducers: {
    setEnigmaType: (state: EnigmaType, action) => {
      state.model = action.payload;
    },
    setRotors: (state: EnigmaType, action) => {
      state.rotors = action.payload;
    },
    setRingSettings: (state: EnigmaType, action) => {
      state.ringSettings = action.payload;
    },
    setRotorPositions: (state: EnigmaType, action) => {
      state.rotorPositions = action.payload;
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
