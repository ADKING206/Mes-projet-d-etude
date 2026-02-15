let backgroudimg = ["../image/backgroud/backgroud image.jpg","../image/backgroud/backgroud image1.jpg","../image/backgroud/backgroud image2.jpg","../image/backgroud/backgroud image3.jpg"];
const Bac=document.getElementById('Bac');
const icleft=document.getElementById('ic-left');
let pointdep=document.querySelectorAll('.pointdep');
console.log(backgroudimg)
let index=0;
icleft.onclick=function(){
    if(index==0){
        index=4;
    }
    index--;
    Bac.src=backgroudimg[index];
    for (let i = 0; i < pointdep.length; i++) {
        pointdep[i].classList.remove('Active');
    }
    pointdep[index].classList.add('Active');
}
const icright=document.getElementById('ic-right');
icright.addEventListener('click',()=>{
    if(index===4){
        index=0;
    }
    Bac.src=backgroudimg[index]
    for (let i = 0; i < pointdep.length; i++) {
        pointdep[i].classList.remove('Active');
    }
    pointdep[index].classList.add('Active');
    index++;
})
setInterval(function(){
    if(index == 4){
        index = 0;
    }
    Bac.src=backgroudimg[index];
    for (let i = 0; i < pointdep.length; i++) {
        pointdep[i].classList.remove('Active');
    }
    pointdep[index].classList.add('Active');
    index++;
},4000);



