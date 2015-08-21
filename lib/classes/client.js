(function() {
  var Client, EventEmitter, PIFaceDigital,
    extend = function(child, parent) { for (var key in parent) { if (hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; },
    hasProp = {}.hasOwnProperty;

  EventEmitter = require('events').EventEmitter;

  PIFaceDigital = require('./pifacedigital');

  module.exports = Client = (function(superClass) {
    extend(Client, superClass);

    function Client() {
      var pi;
      pi = new PIFaceDigital(0);
    }

    return Client;

  })(EventEmitter);

}).call(this);
