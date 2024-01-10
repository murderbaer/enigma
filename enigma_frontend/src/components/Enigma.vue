<script setup lang="ts">
import Rotor from "@components/Rotor.vue";
import EnigmaTextArea from "@components/EnigmaTextArea.vue";

import { EnigmaTypes } from "@constants/EnigmaTypes.ts";
import { ref } from "vue";

const enigmaType = ref(EnigmaTypes.NONE);
const rotors: Array<typeof Rotor> = [];

const msg = ref("");

function setEnigmaType(type: EnigmaTypes) {
  enigmaType.value = type;

  if (type === EnigmaTypes.ENIGMA_M3) {
    for (let i = 0; i < 3; i++) {
      rotors.push(Rotor);
    }
  } else if (type === EnigmaTypes.ENIGMA_M4) {
    for (let i = 0; i < 4; i++) {
      rotors.push(Rotor);
    }
  }
}

function setEnigmaMessage(newMsg: string) {
  newMsg = newMsg.toUpperCase().replace(/[^A-Z]/g, "");

  msg.value = newMsg;
}
</script>

<template>
  <div v-if="enigmaType === EnigmaTypes.NONE">
    <p>Choose an Enigma type</p>
    <button @click="setEnigmaType(EnigmaTypes.ENIGMA_M3)">Enigma M3</button>
    <button @click="setEnigmaType(EnigmaTypes.ENIGMA_M4)">Enigma M4</button>
  </div>

  <div v-else class="enigma-container">
    <div class="rotor-container">
      <div v-for="(rotor, index) in rotors">
        <component :is="rotor" :index="rotors.length - index" />
      </div>
    </div>

    <EnigmaTextArea
      :msg="msg"
      :readonly="false"
      :placeholder="'Enter a message to encrypt'"
      :onMessageChange="setEnigmaMessage"
    />
    <EnigmaTextArea
      :msg="msg.toLowerCase()"
      :readonly="false"
      :placeholder="'Enter a message to encrypt'"
      :onMessageChange="setEnigmaMessage"
    />
  </div>
</template>

<style scoped>
.rotor-container {
  display: flex;
  flex-direction: row;
  justify-content: space-evenly;
  gap: 10px;
}

.enigma-container {
  display: flex;
  flex-direction: column;
  justify-content: space-evenly;
  align-items: center;
}
</style>
