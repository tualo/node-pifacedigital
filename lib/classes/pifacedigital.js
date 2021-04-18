(function() {
  var EventEmitter, PIFaceDigital, e, pifacedigital;

  try {
    pifacedigital = require('../../build/Release/pifacedigital.node');
  } catch (error1) {
    e = error1;
    error('pifacedigital', e);
  }

  ({EventEmitter} = require('events'));

  module.exports = PIFaceDigital = class PIFaceDigital extends EventEmitter {
    constructor(addr, closeOnExit) {
      var fn, i, p, pi;
      super(addr, closeOnExit);
      fn = function() {
        return null;
      };
      this.callbacks = [fn, fn, fn, fn, fn, fn, fn, fn];
      this.states = [0, 0, 0, 0, 0, 0, 0, 0];
      this.timer = [null, null, null, null, null, null, null, null];
      this.pi = pifacedigital;
      this.addr = addr;
      pi = this.pi;
      pi.open(this.addr);
      this.closeOnExit = closeOnExit;
      process.on('exit', this._clean.bind(this));
//process.on 'SIGTERM', @_clean.bind(@)
//process.on 'SIGINT', @_clean.bind(@)
//process.on 'SIGHUP', @_clean.bind(@)
      for (p = i = 0; i <= 7; p = ++i) {
        this.states[p] = this.get(p * 1);
      }
    }

    _clean() {
      if (this.closeOnExit === true) {
        this.pi.set(this.addr, 0, 0);
        this.pi.set(this.addr, 0, 1);
        this.pi.set(this.addr, 0, 2);
        this.pi.set(this.addr, 0, 3);
        this.pi.set(this.addr, 0, 4);
        this.pi.set(this.addr, 0, 5);
        this.pi.set(this.addr, 0, 6);
        return this.pi.set(this.addr, 0, 7);
      }
    }

    set(pin, value) {
      return this.pi.set(this.addr, value * 1, pin * 1);
    }

    get(pin) {
      return this.pi.get(this.addr, pin * 1);
    }

    getInput() {
      return this.pi.getInput(this.addr);
    }

    getOutput() {
      return this.pi.getOutput(this.addr);
    }

    _watch(pin, callback) {
      return this.pi.watch(function(addr1) {
        this.addr = addr1;
        return console.log(arguments);
      });
    }

    //if typeof @callbacks[pin]=='function'
    //  @callbacks[pin] = callback
    //  @_watch pin
    unwatch(pin) {
      if (typeof this.timer[pin] !== 'undefined') {
        return clearTimeout(this.timer[pin]);
      }
    }

    watch(pin, callback) {
      var fn, me, val;
      if (typeof callback === 'function') {
        this.callbacks[pin] = callback;
      }
      val = this.get(this.addr, pin);
      if (this.states[pin] !== val) {
        if (this.states[pin] < val) {
          this.callbacks[pin](pin, 'lohi');
        } else {
          this.callbacks[pin](pin, 'hilo');
        }
      }
      this.states[pin] = val;
      me = this;
      fn = function() {
        return me.watch.bind(me)(pin * 1);
      };
      return this.timer[pin] = setTimeout(fn, 10);
    }

  };

}).call(this);
