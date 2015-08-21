(function() {
  var Client, EventEmitter, PIFaceDigital,
    extend = function(child, parent) { for (var key in parent) { if (hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; },
    hasProp = {}.hasOwnProperty;

  EventEmitter = require('events').EventEmitter;

  PIFaceDigital = require('./pifacedigital');

  module.exports = Client = (function(superClass) {
    extend(Client, superClass);

    function Client() {
      this.pi = new PIFaceDigital(0);
    }

    Client.prototype.watch = function(pin) {
      var fn;
      this.pi.watch(pin, function(pin, state) {
        return console.log(state, pin);
      });
      fn = function() {
        return setTimeout(fn, 10000);
      };
      return setTimeout(fn, 10000);
    };

    Client.prototype.set = function(pin, value) {
      return this.pi.set(pin, value);
    };

    Client.prototype.get = function(pin) {
      return console.log('value', this.pi.get(pin));
    };

    return Client;

  })(EventEmitter);

}).call(this);
