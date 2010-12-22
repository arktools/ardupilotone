using ArducopterConfigurator;
using NUnit.Framework;

namespace ArducopterConfiguratorTest
{
    public abstract class VmTestBase<T> where T : MonitorVm
    {
        protected T _vm;
        protected FakeComms _fakeComms;
        protected string sampleLineOfData; // should be taken from a real APM if possible
        protected string getCommand;
        protected string setCommand;

        [Test]
        public void ActivateSendsCorrectCommand()
        {
            _vm.Activate();
            Assert.AreEqual(1, _fakeComms.SentItems.Count);
            Assert.AreEqual(getCommand, _fakeComms.SentItems[0]);
        }

        [Test]
        public void ReceivedDataIgnoredWhenNotActive()
        {
            bool inpcFired = false;
            _vm.PropertyChanged += delegate { inpcFired = true; };

            _fakeComms.FireLineRecieve(sampleLineOfData);
            Assert.False(inpcFired);
        }

        [Test]
        public void ReceivedDataIgnoredAfterDeActive()
        {
            _vm.Activate();
            _fakeComms.FireLineRecieve(sampleLineOfData);
            _vm.DeActivate();
            _fakeComms.FireLineRecieve(sampleLineOfData);
            bool inpcFired = false;
            _vm.PropertyChanged += delegate { inpcFired = true; };

            Assert.False(inpcFired);
        }

        [Test]
        public void UpdateStringReceivedPopulatesValues()
        {
            bool inpcFired = false;
            _vm.PropertyChanged += delegate { inpcFired = true; };

            _vm.Activate();
            _fakeComms.FireLineRecieve(sampleLineOfData);

            Assert.True(inpcFired);
        }
    }
}