<script setup lang="ts">

    import { defineProps } from 'vue';

    defineProps<{ 
        msg: string,
        readonly: boolean
        placeholder: string,
        onMessageChange: (newMsg: string) => void
    }>()

</script>

<template>
    <input 
        type="text"
        :value="msg"
        :readonly="readonly"
        :placeholder="placeholder"
        @input="(e: Event) => { 
            const target = <HTMLInputElement>(e.target);
            onMessageChange(target.value) 
        }"
    />
</template>