try
  pifacedigital = require '../../build/Release/pifacedigital.node'
catch e
  error 'pifacedigital',e

{EventEmitter} = require 'events'

module.exports =
class PIFaceDigital extends EventEmitter
  constructor: (addr) ->
    console.log(pifacedigital)
    console.log(typeof pifacedigital.PIFaceDigital)
