{Command} = require 'tualo-commander'
path = require 'path'
fs = require 'fs'
{Client} = require '../main'

params = [
  {parameter: "-t, --type [type]", description: "operation type [set|get|watch]"},
  {parameter: "-p, --pin [pin]", description: "pin number"},
  {parameter: "-v, --value [value]", description: "pin value"}
]



module.exports =
class ClientCMD extends Command
  @commandName: 'client'
  @commandArgs: []
  @commandShortDescription: 'run the client'
  @options: params
  @help: () ->
    """

    """

  action: (options,args) ->
    @client = new Client
    fn = () ->
      null
    if options.type == 'set' and options.pin and options.value
      @client.set options.pin, options.value
      setTimeout fn, 1000
    else if options.type == 'get' and options.pin
      @client.get options.pin
      setTimeout fn, 1000
    else if options.type == 'watch' and options.pin
      @client.watch options.pin
    else
      error 'client', 'params are not valid'
