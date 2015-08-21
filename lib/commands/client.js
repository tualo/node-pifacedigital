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
      parameter: "-p, --pin",
      description: "pin number"
    }, {
      parameter: "-v, --value",
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
      if (options.pin && options.value) {
        return this.client = new Client;
      } else {
        return error('client', 'you have to set the pin and value');
      }
    };

    return ClientCMD;

  })(Command);

}).call(this);
