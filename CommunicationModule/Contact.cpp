#include "StableHeaders.h"
#include "Foundation.h"

#include "Contact.h"


namespace TpQt4Communication
{
	Contact::Contact(Tp::ContactPtr tp_contact)
	{
		LogInfo("Create Contact object");
		if (tp_contact.isNull())
		{
			LogError("contact == NULL");
			return;
		}
		assert( !tp_contact.isNull() );
		tp_contact_ = tp_contact;
		presence_message_ = tp_contact_->presenceMessage().toStdString();
		presence_status_ = tp_contact_->presenceStatus().toStdString();
		ConnectSignals();
	}

	void Contact::ConnectSignals()
	{
		if (tp_contact_.isNull())
		{
			LogError("contact == NULL");
			return;
		}

		QObject::connect(tp_contact_.data(),
            SIGNAL(simplePresenceChanged(const QString &, uint, const QString &)),
            SLOT(OnContactChanged()));
		QObject::connect(tp_contact_.data(),
            SIGNAL(subscriptionStateChanged(Tp::Contact::PresenceState)),
            SLOT(OnContactChanged()));
		QObject::connect(tp_contact_.data(),
            SIGNAL(publishStateChanged(Tp::Contact::PresenceState)),
            SLOT(OnContactChanged()));
		QObject::connect(tp_contact_.data(),
            SIGNAL(blockStatusChanged(bool)),
            SLOT(OnContactChanged()));
	}

	void Contact::OnContactChanged()
	{
		LogInfo("Contact state changed");

		QString status =  tp_contact_->presenceStatus();
		QString message =  tp_contact_->presenceMessage();
		presence_status_ = status.toStdString();
		presence_message_ = message.toStdString();

		switch( tp_contact_->subscriptionState() )
		{
			case Tp::Contact::PresenceStateAsk: break;
			case Tp::Contact::PresenceStateNo: break;
			case Tp::Contact::PresenceStateYes: break;
		}
		
		if (tp_contact_->isBlocked())
		{
			// User has blocked this contact
		}
		emit StateChanged();
	}

	Address Contact::GetAddress()
	{
		return tp_contact_->id().toStdString();
	}

	std::string Contact::GetRealName()
	{
		if (tp_contact_.isNull())
			return "NULL";
		else
			return tp_contact_->alias().toStdString();
	}

	std::string Contact::GetPresenceStatus()
	{
		return presence_status_;
	}

	std::string Contact::GetPresenceMessage()
	{
		return presence_message_;
	}

} // end of namespace: Communication