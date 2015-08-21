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
      var fn, pi;
      fn = function() {
        return null;
      };
      this.callbacks = [fn, fn, fn, fn, fn, fn, fn, fn];
      this.states = [0, 0, 0, 0, 0, 0, 0, 0];
      this.timer = [null, null, null, null, null, null, null, null];
      this.pi = new pifacedigital.PIFaceDigital;
      pi = this.pi;
      pi.open();
      process.on('exit', function() {
        if (closeOnExit === true) {
          pi.set(0, 0);
          pi.set(0, 1);
          pi.set(0, 2);
          pi.set(0, 3);
          pi.set(0, 4);
          pi.set(0, 5);
          pi.set(0, 6);
          return pi.set(0, 7);
        }
      });
    }

    PIFaceDigital.prototype.set = function(pin, value) {
      return this.pi.set(value, pin);
    };

    PIFaceDigital.prototype.get = function(pin) {
      return this.pi.get(pin);
    };

    PIFaceDigital.prototype.watch = function(pin, callback) {
      if (typeof this.callbacks[pin] === 'function') {
        return this.callbacks[pin] = callback;
      }
    };

    PIFaceDigital.prototype.unwatch = function(pin) {
      if (typeof this.timer[pin] !== 'undefined') {
        return clearTimeout(this.timer[pin]);
      }
    };

    PIFaceDigital.prototype._watch = function(pin) {
      var val;
      val = this.get(pin);
      if (this.states[pin] !== val) {
        if (this.states[pin] < val) {
          this.callbacks[pin](pin, 'lohi');
        } else {
          this.callbacks[pin](pin, 'hilo');
        }
      }
      return this.timer[pin] = setTimeout(this._watch.bind(this), 10);
    };

    return PIFaceDigital;

  })(EventEmitter);

}).call(this);
