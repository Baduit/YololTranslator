var app = new Vue({
  el: "#app",
  data: {
    title: "YOLOL TRANSLATOR",
    yololInput: "",
    textToTranslate: "",
    newText: false,
    fetching: false,
    translation: ""
  },
  computed: {
    calculating: function() {
      return this.newText ||
        this.yololInput !== this.textToTranslate ||
        this.fetching
        ? "#550000"
        : "transparent";
    }
  },
  methods: {
    copy: function() {
      navigator.clipboard.writeText(this.yololInput);
    },
    getTranslation: function(text) {
      if (
        !this.fetching &&
        this.yololInput === this.textToTranslate &&
        this.newText
      ) {
        this.fetching = true;
        fetch("/translate", {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify({ text: this.yololInput })
        }).then(
          function(res) {
            if (res.status !== 200) {
              this.title = "💀 Failing translator";
            } else {
              this.title = "YOLOL TRANSLATOR";
            }
            res.text().then(text => {
              this.translation = text;
            });
            this.fetching = false;
          }.bind(this)
        );
      }
      if (this.textToTranslate === this.yololInput) {
        this.newText = false;
      }
      if (this.textToTranslate !== this.yololInput) {
        this.newText = true;
        this.textToTranslate = this.yololInput;
      }
    }
  },
  mounted() {
    setInterval(this.getTranslation, 1000);
  }
});
