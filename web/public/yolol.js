var app = new Vue({
  el: "#app",
  data: {
    yololInput: ""
  },
  computed: {
    translation: () => this.yololInput
  },
  methods: {}
});
