
/* Iemesls, kāpēc ģenerētais elements neparādās, ir tāds,
 * ka tas tiek ģenerēts, bet nekad netiek pievienots pašam dokumentam.
 * Lai elements parādītos to jāpievieno ar 'document.appendChild(dd);'
 */

function generateDropDown(){
    let data = [
        {id:1, name:"Tea"},
        {id:2, name:"Coffee"},
        {id:3, name:"Water"}
    ];
    let dd = document.createElement("select");
    for (let i in data) {
        let opt = document.createElement("option");
        opt.value=data[i].id;
        opt.text=data[i].name;
        dd.add(opt);
    }
    // Pievieno elementu dokumenta beigās
    document.appendChild(dd);
}