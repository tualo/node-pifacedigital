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
    if options._optionValues.type == 'set' and options._optionValues.pin and options._optionValues.value
      @client.set options._optionValues.pin, options._optionValues.value
      setTimeout fn, 1000
    else if options._optionValues.type == 'get' and options._optionValues.pin
      @client.get options._optionValues.pin
      setTimeout fn, 1000
    else if options._optionValues.type == 'watch' and options._optionValues.pin
      @client.watch options._optionValues.pin
    else
      console.log options
      error 'client', 'params are not valid'
