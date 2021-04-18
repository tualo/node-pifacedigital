try
  pifacedigital = require '../../build/Release/pifacedigital.node'
catch e
  error 'pifacedigital',e

{EventEmitter} = require 'events'

module.exports =
class PIFaceDigital extends EventEmitter
  constructor: (addr,closeOnExit) ->
    super(addr,closeOnExit)
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

    @pi = pifacedigital
    console.log @pi
    @addr = addr
    pi = @pi
    pi.open(@addr)
    @closeOnExit= closeOnExit
    process.on 'exit', @_clean.bind(@)

    #process.on 'SIGTERM', @_clean.bind(@)
    #process.on 'SIGINT', @_clean.bind(@)
    #process.on 'SIGHUP', @_clean.bind(@)

    for p in [0..7]
      @states[p]=@get p*1

  _clean: () ->
    if @closeOnExit==true
      @pi.set @addr,0,0
      @pi.set @addr,0,1
      @pi.set @addr,0,2
      @pi.set @addr,0,3
      @pi.set @addr,0,4
      @pi.set @addr,0,5
      @pi.set @addr,0,6
      @pi.set @addr,0,7

  set: (pin,value) ->
    @pi.set @addr ,value*1,pin*1

  get: (pin) ->
    @pi.get @addr  ,pin*1

  getInput: () ->
    @pi.getInput(@addr)
    
  getOutput: () ->
    @pi.getOutput(@addr)


  _watch: (pin, callback) ->
    @pi.watch (@addr) ->
      console.log arguments
    #if typeof @callbacks[pin]=='function'
    #  @callbacks[pin] = callback
    #  @_watch pin

  unwatch: (pin) ->
    if typeof @timer[pin]!='undefined'
      clearTimeout @timer[pin]

  watch: (pin,callback) ->
    if typeof callback=='function'
      @callbacks[pin] = callback
    val = @get @addr,pin
    if @states[pin]!=val
      if @states[pin]<val
        @callbacks[pin] pin,'lohi'
      else
        @callbacks[pin] pin,'hilo'
    @states[pin]=val
    me = @
    fn = () ->
      me.watch.bind(me)(pin*1)
    @timer[pin] = setTimeout fn, 10
