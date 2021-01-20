

document.getElementById('nextBtn').onclick = ()=>{

    const { ipcRenderer } = require('electron')

    document.getElementById('nextFibInp').value = ( ipcRenderer.sendSync('getFib') )

}

document.getElementById('clearBtn').onclick = ()=>{

    const { ipcRenderer } = require('electron')

    document.getElementById('nextFibInp').value = ( ipcRenderer.sendSync('clearFib') )

}