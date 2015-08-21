colors = require "colors"
fs = require "fs"
global.logDebug = process.env.log_debug != "0"
global.logInfo = process.env.log_info != "0"
global.logWarn = process.env.log_warn != "0"
global.logError = process.env.log_error != "0"


global.debug = (tag,msg,data) ->
  if global.logDebug == true
    console.log colors.blue('debug'),colors.gray(tag),msg
global.info = (tag,msg) ->
  if global.logInfo == true
    console.log colors.green('info'),colors.gray(tag),msg
global.warn = (tag,msg) ->
  if global.logWarn == true
    console.log colors.yellow('warning'),colors.gray(tag),msg
global.error = (tag,msg) ->
  if global.logError == true
    console.log colors.red('error'),colors.gray(tag),msg


classNames = [
  'PIFaceDigital',
  'Client'
]

exp = (name) ->
  exports[name] = require './classes/'+name.toLowerCase()
( exp(name) for name in classNames)
