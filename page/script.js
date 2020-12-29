async function request(url, method = 'POST'){

    try{
        const headers = {}
     
        const response = await fetch(url,{
            method,
            headers
        })
  
        return await response.json()
  
    }catch(e){
        console.log('Ошибка:', e.message)
    }
}

document.getElementById('nextFibBtn').onclick = async ()=>{

    let res = await request('/nextFib','POST')

    document.getElementById('nextFibInp').value = res


}


