const express = require('express')
const path = require('path')
const get_fibo = require('bindings')('get_fibo')

const PORT = 3000 || process.env.PORT

const app = express()

app.post('/nextFib',(req, res)=>{

    res.status(200).json(get_fibo.get())

})

app.use(express.static(path.resolve(__dirname, 'page')))

app.get('*',(req, res)=>{
    res.sendFile(path.resolve(__dirname,'page','index.html'))
})

app.listen(PORT,()=>console.log(`Приложение запущено на порту ${PORT}`))