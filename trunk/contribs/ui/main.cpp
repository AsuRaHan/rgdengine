int main ()
{
    using namespace ui;

    ////////////////////
    // ������� ������ //
    ////////////////////
    PRender render(new CRender2d());

    ////////////////
    // ������� ui //
    ////////////////
    CUI ui(render);

    //////////////////
    // ��������� ui //
    //////////////////

    //1 (������)
    render.AddImage("panel image", "panel.jpg");
    render.AddFont ("panel font", "arial", 24, FIXED | BOLD | ITALIC);

    CPanel  *pnlMenu  = ui.create<CPanel >("pnlMenu");
    CButton *btnPlay  = ui.create<CButton>("btnPlay");
    CButton *btnExit  = ui.create<CButton>("btnExit");
    CLabel  *lblTitle = ui.create<CLabel >("lblTitle");

    ui.setRoot(pnlMenu);
    pnlMenu.setSize(10,10,300,500);
    pnlMenu.setImage("panel image");
    pnl.bind(btnPlay);
    pnl.bind(btnExit);
    pnl.bind(lblTitle);

    btnPlay.setSize(5,5,290,25);
    btnPlay.setText("Play");
    btnPlay.setFont("panel font");

    btnExit.setSize(5,35,290,25);
    btnExit.setText("Exit");
    btnPlay.setFont("panel font");

    lblTitle.setSize(5,65,290,25);
    lblTitle.setText("TITLE");
    lblTitle.setFont("panel font big");

    //2 (��� ������ xml �������)
    CBuilderXML builder(ui);
    builder.load("ui_config.xml");

    //3 (��� ������ html �������)
    CBuilderHTML builder(ui);
    builder.load("ui_config.html");

    ///////////////////
    // �������� � ui //
    ///////////////////
    while (play)
    {
        ui.injectMouseMove(-5,3);
        ui.injectKeyDown(VK_RETURN);
        ui.injectChar('A');

        ui.render(deltatime);
    }
}