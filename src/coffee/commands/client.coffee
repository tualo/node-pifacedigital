{Command} = require 'tualo-commander'
path = require 'path'
fs = require 'fs'
{Client} = require '../main'

params = [
  {parameter: "-p, --pin", description: "pin number"},
  {parameter: "-v, --value", description: "pin value"}
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
    if options.pin and options.value
      @client = new Client
    else
      error 'client', 'you have to set the pin and value'
