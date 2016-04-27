(function() {
  var EventEmitter, PIFaceDigital, e, pifacedigital,
    extend = function(child, parent) { for (var key in parent) { if (hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; },
    hasProp = {}.hasOwnProperty;

  try {
    pifacedigital = require('../../build/Release/pifacedigital.node');
  } catch (_error) {
    e = _error;
    error('pifacedigital', e);
  }

  EventEmitter = require('events').EventEmitter;

  module.exports = PIFaceDigital = (function(superClass) {
    extend(PIFaceDigital, superClass);

    function PIFaceDigital(addr, closeOnExit) {
      var fn, i, p, pi;
      fn = function() {
        return null;
      };
      this.callbacks = [fn, fn, fn, fn, fn, fn, fn, fn];
      this.states = [0, 0, 0, 0, 0, 0, 0, 0];
      this.timer = [null, null, null, null, null, null, null, null];
      this.pi = new pifacedigital.PIFaceDigital;
      pi = this.pi;
      pi.open(addr);
      this.closeOnExit = closeOnExit;
      process.on('exit', this._clean.bind(this));
      for (p = i = 0; i <= 7; p = ++i) {
        this.states[p] = this.get(p);
      }
    }

    PIFaceDigital.prototype._clean = function() {
      if (this.closeOnExit === true) {
        this.pi.set(0, 0);
        this.pi.set(0, 1);
        this.pi.set(0, 2);
        this.pi.set(0, 3);
        this.pi.set(0, 4);
        this.pi.set(0, 5);
        this.pi.set(0, 6);
        return this.pi.set(0, 7);
      }
    };

    PIFaceDigital.prototype.set = function(pin, value) {
      return this.pi.set(value, pin);
    };

    PIFaceDigital.prototype.get = function(pin) {
      return this.pi.get(pin);
    };

    PIFaceDigital.prototype.getInput = function() {
      return this.pi.getInput();
    };

    PIFaceDigital.prototype._watch = function(pin, callback) {
      return this.pi.watch(function() {
        return console.log(arguments);
      });
    };

    PIFaceDigital.prototype.unwatch = function(pin) {
      if (typeof this.timer[pin] !== 'undefined') {
        return clearTimeout(this.timer[pin]);
      }
    };

    PIFaceDigital.prototype.watch = function(pin, callback) {
      var fn, me, val;
      if (typeof callback === 'function') {
        this.callbacks[pin] = callback;
      }
      val = this.get(pin);
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
        return me.watch.bind(me)(pin);
      };
      return this.timer[pin] = setTimeout(fn, 10);
    };

    return PIFaceDigital;

  })(EventEmitter);

}).call(this);
