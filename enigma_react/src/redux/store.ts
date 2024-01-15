import { EnigmaReducer } from "./slices/enigma_slice";

import { configureStore } from "@reduxjs/toolkit";

export const store = configureStore({
  reducer: {
    enigma: EnigmaReducer,
  },
});

export type RootState = ReturnType<typeof store.getState>;
export type AppDispatch = typeof store.dispatch;
