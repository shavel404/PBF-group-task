const {app, BrowserWindow, ipcMain} = require('electron') 
const url = require('url') 
const path = require('path')  

const { Fibo } = require('./build/Release/fibo') 
const fibo = new Fibo()

let win = null


app.on('ready', function(){
    // Create the window
    win = new BrowserWindow(
        {
            width: 800, 
            height: 600,
            webPreferences: {
                nodeIntegration: true,
                preload: ('file://' + __dirname + '/script.js')
              }
        },
       
        )

    win.loadURL('file://' + __dirname + '/index.html')

    win.on('closed', () => {
        win = null
    });
})

app.on('window-all-closed', () => {
    app.quit()
})

ipcMain.on('getFib', (event, arg) => {
    event.returnValue = fibo.get()
})

ipcMain.on('clearFib', (event, arg) => {
   event.returnValue = fibo.clear()
})

