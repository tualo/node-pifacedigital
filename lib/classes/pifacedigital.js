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

    function PIFaceDigital(addr) {
      console.log(pifacedigital);
      console.log(typeof pifacedigital.PIFaceDigital);
    }

    return PIFaceDigital;

  })(EventEmitter);

}).call(this);
