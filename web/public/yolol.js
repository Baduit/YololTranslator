var app = new Vue({
  el: "#app",
  data: {
    yololInput: ""
  },
  computed: {
    translation: () => {
      console.log(this);
      return this.yololInput;
    }
  },
  methods: {}
});
