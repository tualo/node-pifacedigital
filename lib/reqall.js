(function() {
  var fs, path;

  fs = require('fs');

  path = require('path');

  module.exports = function(pathName, extension) {
    var entry, files, result;
    result = [];
    files = fs.readdirSync(path.join(__dirname, pathName));
    (function() {
      var i, len, results;
      results = [];
      for (i = 0, len = files.length; i < len; i++) {
        entry = files[i];
        if (path.extname(entry) === extension) {
          results.push(result.push(entry));
        }
      }
      return results;
    })();
    return result;
  };

}).call(this);
