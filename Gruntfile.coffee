fs = require 'fs'
path = require 'path'

module.exports = (grunt) ->
  grunt.initConfig
    pkg: grunt.file.readJSON('package.json')

    coffee:
      app:
        expand: true
        cwd: 'src/coffee'
        src: ['**/*.coffee']
        dest: 'lib'
        ext: '.js'

    coffeelint:
      options:
        #no_empty_param_list:
        #  level: 'error'
        max_line_length:
          level: 'ignore'

      src: ['src/**/*.coffee']
      test: ['spec/*.coffee']
      gruntfile: ['Gruntfile.coffee']


  grunt.loadNpmTasks 'grunt-contrib-coffee'
  grunt.loadNpmTasks 'grunt-coffeelint'

  grunt.registerTask 'createcommands', ->
    commandList = require('./lib/reqall')('./commands','.js')
    commands = []
    (commands.push(require('./lib/commands/'+path.basename(name))) for name in commandList when name!='command.js')

    for command in commands
      file = path.join(__dirname,'bin','sorter-'+command.commandName)
      options =
        mode: 511
      data = """
      #!/usr/bin/env node
      Cli = require('tualo-commander').Cli;
      cli = new Cli();
      cli.main('"""+command.commandName+"""');

      """
      fs.writeFileSync file, data, options


  grunt.registerTask('lint', ['coffeelint'])
  grunt.registerTask 'default', ['coffee','createcommands','lint']
  grunt.registerTask 'clean', ->
    grunt.file.delete('lib') if grunt.file.exists('lib')
