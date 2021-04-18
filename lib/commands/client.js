(function() {
  var Client, ClientCMD, Command, fs, params, path;

  ({Command} = require('tualo-commander'));

  path = require('path');

  fs = require('fs');

  ({Client} = require('../main'));

  params = [
    {
      parameter: "-t, --type [type]",
      description: "operation type [set|get|watch]"
    },
    {
      parameter: "-p, --pin [pin]",
      description: "pin number"
    },
    {
      parameter: "-v, --value [value]",
      description: "pin value"
    }
  ];

  module.exports = ClientCMD = (function() {
    class ClientCMD extends Command {
      static help() {
        return ``;
      }

      action(options, args) {
        var fn;
        this.client = new Client();
        fn = function() {
          return null;
        };
        if (options._optionValues.type === 'set' && options._optionValues.pin && options._optionValues.value) {
          this.client.set(options._optionValues.pin, options._optionValues.value);
          return setTimeout(fn, 1000);
        } else if (options._optionValues.type === 'get' && options._optionValues.pin) {
          this.client.get(options._optionValues.pin);
          return setTimeout(fn, 1000);
        } else if (options._optionValues.type === 'watch' && options._optionValues.pin) {
          return this.client.watch(options._optionValues.pin);
        } else {
          console.log(options);
          return error('client', 'params are not valid');
        }
      }

    };

    ClientCMD.commandName = 'client';

    ClientCMD.commandArgs = [];

    ClientCMD.commandShortDescription = 'run the client';

    ClientCMD.options = params;

    return ClientCMD;

  }).call(this);

}).call(this);
