(function() {
  var Client, EventEmitter, PIFaceDigital;

  ({EventEmitter} = require('events'));

  PIFaceDigital = require('./pifacedigital');

  module.exports = Client = class Client extends EventEmitter {
    constructor() {
      super();
      this.pi = new PIFaceDigital(0);
    }

    watch(pin) {
      var fn;
      this.pi.watch(pin, function(pin, state) {
        return console.log(state, pin);
      });
      fn = function() {
        return setTimeout(fn, 10000);
      };
      return setTimeout(fn, 10000);
    }

    set(pin, value) {
      return this.pi.set(pin, value);
    }

    get(pin) {
      return console.log('value', this.pi.get(pin));
    }

  };

}).call(this);
