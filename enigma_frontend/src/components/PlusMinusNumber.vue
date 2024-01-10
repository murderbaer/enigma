<template>
  <div>
    <h4>{{ label }}</h4>
    <button @click="decrement">-</button>
    <label for="rotor-position" hidden>{{ label }}</label>
    <input type="number" id="rotor-position" :value="value + 1" />
    <button @click="increment">+</button>
  </div>
</template>
<script setup lang="ts">
defineProps<{
  value: number;
  increment: () => void;
  decrement: () => void;
  label: string;
}>();
</script>
<style lang=""></style>
