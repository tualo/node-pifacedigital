(function() {
  var classNames, colors, exp, fs, name;

  colors = require("colors");

  fs = require("fs");

  global.logDebug = process.env.log_debug !== "0";

  global.logInfo = process.env.log_info !== "0";

  global.logWarn = process.env.log_warn !== "0";

  global.logError = process.env.log_error !== "0";

  global.debug = function(tag, msg, data) {
    if (global.logDebug === true) {
      return console.log(colors.blue('debug'), colors.gray(tag), msg);
    }
  };

  global.info = function(tag, msg) {
    if (global.logInfo === true) {
      return console.log(colors.green('info'), colors.gray(tag), msg);
    }
  };

  global.warn = function(tag, msg) {
    if (global.logWarn === true) {
      return console.log(colors.yellow('warning'), colors.gray(tag), msg);
    }
  };

  global.error = function(tag, msg) {
    if (global.logError === true) {
      return console.log(colors.red('error'), colors.gray(tag), msg);
    }
  };

  classNames = ['PIFaceDigital', 'Client'];

  exp = function(name) {
    return exports[name] = require('./classes/' + name.toLowerCase());
  };

  (function() {
    var i, len, results;
    results = [];
    for (i = 0, len = classNames.length; i < len; i++) {
      name = classNames[i];
      results.push(exp(name));
    }
    return results;
  })();

}).call(this);
