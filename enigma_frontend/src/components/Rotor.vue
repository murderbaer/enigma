<template>
  <div class="rotor" v-if="selectedRotor == null">
    <h3 class="rotor-title">Rotor {{ index }}</h3>
    <select @click="onChange($event)">
      <option v-for="rotorType in rotorTypes" :value="rotorType">
        {{ rotorType }}
      </option>
      <option value="" selected disabled hidden>Select</option>
    </select>
  </div>

  <div class="rotor" v-else>
    <select @click="onChange($event)">
      <option
        v-for="rotorType in rotorTypes"
        :value="rotorType"
        :selected="rotorType === selectedRotor"
      >
        {{ rotorType }}
      </option>
    </select>

    <PlusMinusNumber
      :value="state.rotorPosition"
      :increment="() => incrementRing('rotorPosition')"
      :decrement="() => decrementRing('rotorPosition')"
      :label="'Rotor Position'"
    />
    <PlusMinusNumber
      :value="state.ringSetting"
      :increment="() => incrementRing('ringSetting')"
      :decrement="() => decrementRing('ringSetting')"
      :label="'Ring Setting'"
    />
  </div>
</template>

<script setup lang="ts">
import Rotors from "@constants/Rotors.ts";
import { reactive, ref } from "vue";
import PlusMinusNumber from "./PlusMinusNumber.vue";

defineProps<{ index: number }>();

let rotorTypes = Object.keys(Rotors);
const selectedRotor = ref<string | null>(null);
const state = reactive({
  rotorPosition: 0,
  ringSetting: 0,
});

function onChange($event: Event) {
  selectedRotor.value = ($event.target as HTMLSelectElement).value;
}

function incrementRing(key: keyof typeof state) {
  if (state[key] === 25) {
    state[key] = 0;
  } else {
    state[key]++;
  }
}

function decrementRing(key: keyof typeof state) {
  if (state[key] === 0) {
    state[key] = 25;
  } else {
    state[key]--;
  }
}
</script>

<style>
.rotor {
  border: 1px solid gray;
  border-radius: 10px;
  padding: 15px;
}
</style>
