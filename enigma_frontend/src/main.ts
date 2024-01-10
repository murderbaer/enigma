import { createApp } from "vue";
import { createStore } from "vuex";
import "./style.css";
import App from "./App.vue";

const store = createStore({
  state() {
    return {
      count: 0,
    };
  },
  mutations: {
    increment(state) {
      state.count++;
    },
  },
});

createApp(App).mount("#app");
