{EventEmitter} = require 'events'
PIFaceDigital = require './pifacedigital'

module.exports =
class Client extends EventEmitter
  constructor: () ->
    pi = new PIFaceDigital 0
