{EventEmitter} = require 'events'
PIFaceDigital = require './pifacedigital'

module.exports =
class Client extends EventEmitter
  constructor: () ->
    @pi = new PIFaceDigital 0

  watch: (pin) ->
    @pi.watch pin, (pin,state) ->
      console.log state,pin

    fn = () ->
      setTimeout fn, 10000
    setTimeout fn, 10000

  set: (pin,value) ->
    @pi.set pin, value

  get: (pin) ->
    console.log 'value', @pi.get(pin)
