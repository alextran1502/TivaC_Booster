
Vue.component('nav-bar', {
  template: `    
  <div > 
    <img src="https://www.conductix.us/sites/all/themes/cxw_us/logo.png"
      alt="Conductix Wampfler | Nexus Narrowband" style="margin-right: 5rem;">
    <span class="app-title">Nexus Narrowband Configuration</span>
  </div>`
});


var app = new Vue({
  el: '#app',
  data: {
    message: 'You loaded this page on ' + new Date().toLocaleString(),
    selected: '',
    value: ''
  },

  // Event Life Cycle
  created: function() {
    console.log('Vue Instance created');
  },

  // Methods
  methods: {
    toggleLed: function() {
      req = new XMLHttpRequest();
      if (req) {
        req.open('GET', '/cgi-bin/toggle_led?id' + Math.random(), true);

        req.onreadystatechange = function() {
          if (req.readyState == 4) {
            if (req.status == 200) {
              this.message = req.responseText;
            }
          }
        }.bind(this);

        req.send(null);
      }
    },

    test: function() {
      req = new XMLHttpRequest();
      if (req) {
        req.open('GET', '/status?id=15', true);
        req.onreadystatechange = function() {
          if (req.readyState == 4) {
            if (req.status == 200) {
              this.message = req.responseText;
            }
          }
        }.bind(this);

        req.send(null);
      }
    },

    onSubmit() {
      console.log(this.value);
    }
  },

  computed: {
    getCurrentYear: function() {
      return new Date().getFullYear();
    }
  }
});
