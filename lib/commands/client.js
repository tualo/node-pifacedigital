(function() {
  var Client, ClientCMD, Command, fs, params, path,
    extend = function(child, parent) { for (var key in parent) { if (hasProp.call(parent, key)) child[key] = parent[key]; } function ctor() { this.constructor = child; } ctor.prototype = parent.prototype; child.prototype = new ctor(); child.__super__ = parent.prototype; return child; },
    hasProp = {}.hasOwnProperty;

  Command = require('tualo-commander').Command;

  path = require('path');

  fs = require('fs');

  Client = require('../main').Client;

  params = [
    {
      parameter: "-t, --type [type]",
      description: "operation type [set|get|watch]"
    }, {
      parameter: "-p, --pin [pin]",
      description: "pin number"
    }, {
      parameter: "-v, --value [value]",
      description: "pin value"
    }
  ];

  module.exports = ClientCMD = (function(superClass) {
    extend(ClientCMD, superClass);

    function ClientCMD() {
      return ClientCMD.__super__.constructor.apply(this, arguments);
    }

    ClientCMD.commandName = 'client';

    ClientCMD.commandArgs = [];

    ClientCMD.commandShortDescription = 'run the client';

    ClientCMD.options = params;

    ClientCMD.help = function() {
      return "";
    };

    ClientCMD.prototype.action = function(options, args) {
      var fn;
      this.client = new Client;
      fn = function() {
        return null;
      };
      if (options.type === 'set' && options.pin && options.value) {
        this.client.set(options.pin, options.value);
        return setTimeout(fn, 1000);
      } else if (options.type === 'get' && options.pin) {
        this.client.get(options.pin);
        return setTimeout(fn, 1000);
      } else if (options.type === 'watch' && options.pin) {
        return this.client.watch(options.pin);
      } else {
        return error('client', 'params are not valid');
      }
    };

    return ClientCMD;

  })(Command);

}).call(this);
