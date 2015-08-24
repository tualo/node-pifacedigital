try
  pifacedigital = require '../../build/Release/pifacedigital.node'
catch e
  error 'pifacedigital',e

{EventEmitter} = require 'events'

module.exports =
class PIFaceDigital extends EventEmitter
  constructor: (addr,closeOnExit) ->
    fn = () ->
      null
    @callbacks = [
      fn,
      fn,
      fn,
      fn,
      fn,
      fn,
      fn,
      fn
    ]

    @states = [
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0
    ]

    @timer = [
      null,
      null,
      null,
      null,
      null,
      null,
      null,
      null
    ]

    @pi = new pifacedigital.PIFaceDigital
    pi = @pi
    pi.open()
    @closeOnExit= closeOnExit
    process.on 'exit', @_clean.bind(@)
    process.on 'SIGTERM', @_clean.bind(@)
    process.on 'SIGINT', @_clean.bind(@)
    process.on 'SIGHUP', @_clean.bind(@)

    for p in [0..7]
      @states[p]=@get p

  _clean: () ->
    if @closeOnExit==true
      @pi.set 0,0
      @pi.set 0,1
      @pi.set 0,2
      @pi.set 0,3
      @pi.set 0,4
      @pi.set 0,5
      @pi.set 0,6
      @pi.set 0,7
      
  set: (pin,value) ->
    @pi.set value,pin

  get: (pin) ->
    @pi.get pin

  getInput: () ->
    @pi.getInput()

  watch: (pin, callback) ->
    if typeof @callbacks[pin]=='function'
      @callbacks[pin] = callback
      @_watch pin

  unwatch: (pin) ->
    if typeof @timer[pin]!='undefined'
      clearTimeout @timer[pin]

  _watch: (pin) ->

    val = @get pin
    if @states[pin]!=val
      if @states[pin]<val
        @callbacks[pin] pin,'lohi'
      else
        @callbacks[pin] pin,'hilo'
    @states[pin]=val
    me = @
    fn = () ->
      me._watch.bind(me)(pin)
    @timer[pin] = setTimeout fn, 10
